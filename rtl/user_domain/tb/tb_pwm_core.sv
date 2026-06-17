module tb_pwm_core;

  localparam int unsigned Width = 16;
  localparam time Tclk = 10ns;

  logic clk_i;
  logic rst_ni;

  logic enable_i;
  logic polarity_i;
  logic [Width-1:0] period_cfg_i;
  logic [Width-1:0] duty_cfg_i;

  logic pwm_o;
  logic [Width-1:0] counter_o;
  logic [Width-1:0] period_active_o;
  logic [Width-1:0] duty_active_o;
  logic period_done_o;
  logic period_zero_o;

  int unsigned errors;

  pwm_core #(
    .Width ( Width )
  ) i_dut (
    .clk_i,
    .rst_ni,

    .enable_i   ( enable_i   ),
    .polarity_i ( polarity_i ),

    .period_cfg_i ( period_cfg_i ),
    .duty_cfg_i   ( duty_cfg_i   ),

    .pwm_o           ( pwm_o           ),
    .counter_o       ( counter_o       ),
    .period_active_o ( period_active_o ),
    .duty_active_o   ( duty_active_o   ),
    .period_done_o   ( period_done_o   ),
    .period_zero_o   ( period_zero_o   )
  );

  initial begin
    clk_i = 1'b0;
    forever #(Tclk/2) clk_i = ~clk_i;
  end

  function automatic logic expected_pwm(
    input int unsigned counter,
    input int unsigned period,
    input int unsigned duty,
    input logic polarity
  );
    int unsigned duty_clamped;
    logic raw;

    begin
      if (period == 0) begin
        expected_pwm = 1'b0;
      end else begin
        if (duty >= period) begin
          duty_clamped = period;
        end else begin
          duty_clamped = duty;
        end

        raw = (counter < duty_clamped);
        expected_pwm = polarity ? ~raw : raw;
      end
    end
  endfunction

  task automatic check_current(
    input string name,
    input int unsigned exp_counter,
    input int unsigned exp_period,
    input int unsigned exp_duty,
    input logic exp_polarity
  );
    logic exp_pwm;
    logic exp_done;
    int unsigned exp_duty_clamped;

    begin
      exp_pwm = expected_pwm(exp_counter, exp_period, exp_duty, exp_polarity);
      exp_done = (exp_period != 0) && (exp_counter == exp_period - 1);

      if (exp_duty >= exp_period) begin
        exp_duty_clamped = exp_period;
      end else begin
        exp_duty_clamped = exp_duty;
      end

      if (counter_o !== exp_counter[Width-1:0]) begin
        $display("[ERROR] %s: counter expected %0d, got %0d at t=%0t",
                 name, exp_counter, counter_o, $time);
        errors++;
      end

      if (period_active_o !== exp_period[Width-1:0]) begin
        $display("[ERROR] %s: period_active expected %0d, got %0d at t=%0t",
                 name, exp_period, period_active_o, $time);
        errors++;
      end

      if (duty_active_o !== exp_duty_clamped[Width-1:0]) begin
        $display("[ERROR] %s: duty_active expected %0d, got %0d at t=%0t",
                 name, exp_duty_clamped, duty_active_o, $time);
        errors++;
      end

      if (pwm_o !== exp_pwm) begin
        $display("[ERROR] %s: pwm_o expected %0b, got %0b at counter=%0d t=%0t",
                 name, exp_pwm, pwm_o, counter_o, $time);
        errors++;
      end

      if (period_done_o !== exp_done) begin
        $display("[ERROR] %s: period_done expected %0b, got %0b at counter=%0d t=%0t",
                 name, exp_done, period_done_o, counter_o, $time);
        errors++;
      end
    end
  endtask

  task automatic start_pwm(
    input int unsigned period,
    input int unsigned duty,
    input logic polarity
  );
    begin
      enable_i     = 1'b0;
      polarity_i   = polarity;
      period_cfg_i = period[Width-1:0];
      duty_cfg_i   = duty[Width-1:0];

      @(posedge clk_i);
      #1;

      enable_i = 1'b1;

      // First enabled clock loads active period/duty and sets counter to zero.
      
      #1;
    end
  endtask

  task automatic check_cycles(
    input string name,
    input int unsigned period,
    input int unsigned duty,
    input logic polarity,
    input int unsigned num_cycles
  );
    int unsigned exp_counter;

    begin
      for (int unsigned i = 0; i < num_cycles; i++) begin
        if (period == 0) begin
          exp_counter = 0;
        end else begin
          exp_counter = i % period;
        end

        check_current(name, exp_counter, period, duty, polarity);

        @(posedge clk_i);
        #1;
      end
    end
  endtask

  initial begin
    $dumpfile("tb_pwm_core.fst");
    $dumpvars(0, tb_pwm_core);

    errors = 0;

    rst_ni       = 1'b0;
    enable_i     = 1'b0;
    polarity_i   = 1'b0;
    period_cfg_i = '0;
    duty_cfg_i   = '0;

    repeat (3) @(posedge clk_i);
    rst_ni = 1'b1;
    @(posedge clk_i);
    #1;

    $display("[TB] Test 1: period=10, duty=3, active-high");
    start_pwm(10, 3, 1'b0);
    check_cycles("period10_duty3", 10, 3, 1'b0, 25);

    $display("[TB] Test 2: period=8, duty=0, always low");
    start_pwm(8, 0, 1'b0);
    check_cycles("period8_duty0", 8, 0, 1'b0, 18);

    $display("[TB] Test 3: period=8, duty=12, duty clamps to period");
    start_pwm(8, 12, 1'b0);
    check_cycles("period8_duty12", 8, 12, 1'b0, 18);

    $display("[TB] Test 4: period=8, duty=2, active-low polarity");
    start_pwm(8, 2, 1'b1);
    check_cycles("period8_duty2_polarity", 8, 2, 1'b1, 18);

    $display("[TB] Test 5: period=0, invalid period forces low");
    start_pwm(0, 3, 1'b0);

    if (pwm_o !== 1'b0) begin
      $display("[ERROR] period0: pwm_o should be low");
      errors++;
    end

    if (period_zero_o !== 1'b1) begin
      $display("[ERROR] period0: period_zero_o should be high");
      errors++;
    end

    if (errors == 0) begin
      $display("[TB] PWM core test PASSED");
    end else begin
      $display("[TB] PWM core test FAILED with %0d errors", errors);
      $fatal(1);
    end

    $finish;
  end

endmodule