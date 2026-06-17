`timescale 1ns/1ps

module tb_pwm_core_file;

  parameter T_CLK_HI   = 5ns;
  parameter T_CLK_LO   = 5ns;
  localparam T_CLK     = T_CLK_HI + T_CLK_LO;
  parameter T_APPL_DEL = 1ns;
  parameter T_ACQ_DEL  = 1ns;

  parameter STIMULI_FILE  = "./stimuli/stimuli.txt";
  parameter RESPONSE_FILE = "./stimuli/expected_response.txt";

  localparam int unsigned Width = 16;

  typedef struct packed {
    logic        polarity;
    logic [15:0] period;
    logic [15:0] duty;
    logic [15:0] samples;
  } stimuli_t;

  typedef struct packed {
    logic        pwm;
    logic        period_done;
    logic        period_zero;
    logic [15:0] counter;
    logic [15:0] period_active;
    logic [15:0] duty_active;
  } exp_rsp_t;

  logic clk;
  logic rst_n;
  logic eoc;

  stimuli_t stimuli[];
  exp_rsp_t exp_response[];

  logic enable_i;
  logic polarity_i;
  logic [15:0] period_cfg_i;
  logic [15:0] duty_cfg_i;

  logic pwm_o;
  logic [15:0] counter_o;
  logic [15:0] period_active_o;
  logic [15:0] duty_active_o;
  logic period_done_o;
  logic period_zero_o;

  int unsigned rsp_idx;
  int unsigned errors;

  pwm_core #(
    .Width ( Width )
  ) i_dut (
    .clk_i           ( clk             ),
    .rst_ni          ( rst_n           ),
    .enable_i        ( enable_i        ),
    .polarity_i      ( polarity_i      ),
    .period_cfg_i    ( period_cfg_i    ),
    .duty_cfg_i      ( duty_cfg_i      ),
    .pwm_o           ( pwm_o           ),
    .counter_o       ( counter_o       ),
    .period_active_o ( period_active_o ),
    .duty_active_o   ( duty_active_o   ),
    .period_done_o   ( period_done_o   ),
    .period_zero_o   ( period_zero_o   )
  );

  //------------------ Clock ------------------//

  initial begin
    clk = 1'b0;
    do begin
      clk = 1'b1; #T_CLK_HI;
      clk = 1'b0; #T_CLK_LO;
    end while (eoc == 1'b0);
  end

  //------------------ Main test ------------------//

  initial begin
    eoc          = 1'b0;
    errors       = 0;
    rsp_idx      = 0;

    rst_n        = 1'b0;
    enable_i     = 1'b0;
    polarity_i   = 1'b0;
    period_cfg_i = '0;
    duty_cfg_i   = '0;

    $dumpfile("tb_pwm_core_file.fst");
    $dumpvars(0, tb_pwm_core_file);

    $display("[TB] Loading stimuli from %s", STIMULI_FILE);
    load_stimuli(STIMULI_FILE);

    $display("[TB] Loading expected responses from %s", RESPONSE_FILE);
    load_exp_response(RESPONSE_FILE);

    // Reset for a few cycles.
    repeat (3) @(posedge clk);
    #T_APPL_DEL;
    rst_n = 1'b1;

    @(posedge clk);
    #T_APPL_DEL;

    foreach (stimuli[i]) begin
      $display("[TB] Vector %0d: polarity=%0d period=%0d duty=%0d samples=%0d",
               i, stimuli[i].polarity, stimuli[i].period,
               stimuli[i].duty, stimuli[i].samples);

      // Disable PWM and apply new configuration.
      enable_i     = 1'b0;
      polarity_i   = stimuli[i].polarity;
      period_cfg_i = stimuli[i].period;
      duty_cfg_i   = stimuli[i].duty;

      @(posedge clk);
      #T_APPL_DEL;

      // Enable PWM. On this clock edge, pwm_core loads active period/duty.
      enable_i = 1'b1;

      
      #T_ACQ_DEL;

      for (int unsigned j = 0; j < stimuli[i].samples; j++) begin
        check_response(i, j, rsp_idx);
        rsp_idx++;

        @(posedge clk);
        #T_ACQ_DEL;
      end
    end

    if (rsp_idx != exp_response.size()) begin
      $display("[ERROR] Used %0d expected responses, but file contains %0d",
               rsp_idx, exp_response.size());
      errors++;
    end

    if (errors == 0) begin
      $display("[TB] PWM file-based test PASSED");
    end else begin
      $display("[TB] PWM file-based test FAILED with %0d errors", errors);
      $fatal(1);
    end

    $dumpflush;
    eoc = 1'b1;
    $finish;
  end

  //------------------ Response check ------------------//

  task automatic check_response(
    input int unsigned vector_idx,
    input int unsigned sample_idx,
    input int unsigned response_idx
  );
    exp_rsp_t exp;

    begin
      exp = exp_response[response_idx];

      if (pwm_o !== exp.pwm ||
          period_done_o !== exp.period_done ||
          period_zero_o !== exp.period_zero ||
          counter_o !== exp.counter ||
          period_active_o !== exp.period_active ||
          duty_active_o !== exp.duty_active) begin

        $display("[ERROR] vec=%0d sample=%0d rsp_idx=%0d time=%0t",
                 vector_idx, sample_idx, response_idx, $time);

        $display("        expected: pwm=%0b done=%0b zero=%0b counter=%0d period_active=%0d duty_active=%0d",
                 exp.pwm, exp.period_done, exp.period_zero,
                 exp.counter, exp.period_active, exp.duty_active);

        $display("        actual:   pwm=%0b done=%0b zero=%0b counter=%0d period_active=%0d duty_active=%0d",
                 pwm_o, period_done_o, period_zero_o,
                 counter_o, period_active_o, duty_active_o);

        errors++;
      end
    end
  endtask

  //------------------ Load stimuli ------------------//

  task load_stimuli(input string filename);
    int file;
    automatic int i = 0;
    string line;
    automatic int line_count = 0;
    logic [63:0] temp;

    file = $fopen(filename, "r");
    if (file == 0) begin
      $fatal(1, "Error: Failed to open file '%s'", filename);
    end

    while (!$feof(file)) begin
      if ($fgets(line, file) != 0) begin
        if (line.len() > 1) begin
          line_count++;
        end
      end
    end
    $fclose(file);

    stimuli = new[line_count];

    file = $fopen(filename, "r");
    while (!$feof(file)) begin
      if ($fgets(line, file) != 0) begin
        if (line.len() > 1) begin
          if ($sscanf(line, "%b", temp) != 1) begin
             $fatal(1, "Could not parse binary line: %s", line);
          end

          stimuli[i].polarity = temp[48];
          stimuli[i].period   = temp[47:32];
          stimuli[i].duty     = temp[31:16];
          stimuli[i].samples  = temp[15:0];

          i++;
        end
      end
    end
    $fclose(file);
  endtask

  //------------------ Load expected responses ------------------//

  task load_exp_response(input string filename);
    int file;
    automatic int i = 0;
    string line;
    automatic int line_count = 0;
    logic [63:0] temp;

    file = $fopen(filename, "r");
    if (file == 0) begin
      $fatal(1, "Error: Failed to open file '%s'", filename);
    end

    while (!$feof(file)) begin
      if ($fgets(line, file) != 0) begin
        if (line.len() > 1) begin
          line_count++;
        end
      end
    end
    $fclose(file);

    exp_response = new[line_count];

    file = $fopen(filename, "r");
    while (!$feof(file)) begin
      if ($fgets(line, file) != 0) begin
        if (line.len() > 1) begin
          if ($sscanf(line, "%b", temp) != 1) begin
             $fatal(1, "Could not parse binary line: %s", line);
          end

          exp_response[i].pwm           = temp[50];
          exp_response[i].period_done   = temp[49];
          exp_response[i].period_zero   = temp[48];
          exp_response[i].counter       = temp[47:32];
          exp_response[i].period_active = temp[31:16];
          exp_response[i].duty_active   = temp[15:0];

          i++;
        end
      end
    end
    $fclose(file);
  endtask

endmodule