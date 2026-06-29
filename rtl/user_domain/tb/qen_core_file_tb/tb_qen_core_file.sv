module tb_qen_core_file;

  localparam int unsigned PosWidth    = 32;
  localparam int unsigned SampleWidth = 32;
  localparam time Tclk = 10ns;

  logic clk_i;
  logic rst_ni;

  logic enable_i;
  logic clear_position_i;
  logic clear_error_i;
  logic index_reset_enable_i;

  logic [SampleWidth-1:0] sample_period_i;

  logic a_i;
  logic b_i;
  logic z_i;

  logic signed [PosWidth-1:0] position_o;
  logic signed [PosWidth-1:0] velocity_o;
  logic signed [PosWidth-1:0] delta_o;
  logic direction_o;
  logic index_seen_o;
  logic signed [PosWidth-1:0] index_position_o;
  logic [31:0] error_count_o;
  logic invalid_transition_o;
  logic velocity_valid_o;
  logic [1:0] ab_state_o;

  int unsigned errors;
  int unsigned num_vectors;

  int stim_fd;
  int exp_fd;
  int stim_rc;
  int exp_rc;

  int stim_cycle;
  int stim_enable;
  int stim_clear_position;
  int stim_clear_error;
  int stim_index_reset_enable;
  int stim_sample_period;
  int stim_a;
  int stim_b;
  int stim_z;

  int exp_cycle;
  int signed exp_position;
  int signed exp_velocity;
  int signed exp_delta;
  int exp_direction;
  int exp_index_seen;
  int signed exp_index_position;
  int unsigned exp_error_count;
  int exp_invalid_transition;
  int exp_velocity_valid;
  int exp_ab_state;

  logic signed [PosWidth-1:0] exp_position_vec;
  logic signed [PosWidth-1:0] exp_velocity_vec;
  logic signed [PosWidth-1:0] exp_delta_vec;
  logic signed [PosWidth-1:0] exp_index_position_vec;
  logic [31:0] exp_error_count_vec;
  logic [1:0] exp_ab_state_vec;

  qen_core #(
    .PosWidth    ( PosWidth    ),
    .SampleWidth ( SampleWidth )
  ) i_dut (
    .clk_i,
    .rst_ni,

    .enable_i             ( enable_i             ),
    .clear_position_i     ( clear_position_i     ),
    .clear_error_i        ( clear_error_i        ),
    .index_reset_enable_i ( index_reset_enable_i ),

    .sample_period_i ( sample_period_i ),

    .a_i ( a_i ),
    .b_i ( b_i ),
    .z_i ( z_i ),

    .position_o,
    .velocity_o,
    .delta_o,
    .direction_o,
    .index_seen_o,
    .index_position_o,
    .error_count_o,
    .invalid_transition_o,
    .velocity_valid_o,
    .ab_state_o
  );

  initial begin
    clk_i = 1'b0;
    forever #(Tclk/2) clk_i = ~clk_i;
  end

  // Watchdog: prevents silent infinite simulations if file reading or
  // control flow breaks. This is cycle-based, so it does not depend on
  // simulator time-unit interpretation.
  initial begin
    repeat (20000) @(posedge clk_i);
    $display("[ERROR] Watchdog timeout after 20000 clock cycles");
    $fatal(1);
  end

  task automatic check_current;
    begin
      exp_position_vec       = exp_position;
      exp_velocity_vec       = exp_velocity;
      exp_delta_vec          = exp_delta;
      exp_index_position_vec = exp_index_position;
      exp_error_count_vec    = exp_error_count[31:0];
      exp_ab_state_vec       = exp_ab_state[1:0];

      if (position_o !== exp_position_vec) begin
        $display("[ERROR] cycle=%0d position expected %0d got %0d at t=%0t",
                 exp_cycle, exp_position_vec, position_o, $time);
        errors++;
      end

      if (velocity_o !== exp_velocity_vec) begin
        $display("[ERROR] cycle=%0d velocity expected %0d got %0d at t=%0t",
                 exp_cycle, exp_velocity_vec, velocity_o, $time);
        errors++;
      end

      if (delta_o !== exp_delta_vec) begin
        $display("[ERROR] cycle=%0d delta expected %0d got %0d at t=%0t",
                 exp_cycle, exp_delta_vec, delta_o, $time);
        errors++;
      end

      if (direction_o !== exp_direction[0]) begin
        $display("[ERROR] cycle=%0d direction expected %0b got %0b at t=%0t",
                 exp_cycle, exp_direction[0], direction_o, $time);
        errors++;
      end

      if (index_seen_o !== exp_index_seen[0]) begin
        $display("[ERROR] cycle=%0d index_seen expected %0b got %0b at t=%0t",
                 exp_cycle, exp_index_seen[0], index_seen_o, $time);
        errors++;
      end

      if (index_position_o !== exp_index_position_vec) begin
        $display("[ERROR] cycle=%0d index_position expected %0d got %0d at t=%0t",
                 exp_cycle, exp_index_position_vec, index_position_o, $time);
        errors++;
      end

      if (error_count_o !== exp_error_count_vec) begin
        $display("[ERROR] cycle=%0d error_count expected %0d got %0d at t=%0t",
                 exp_cycle, exp_error_count_vec, error_count_o, $time);
        errors++;
      end

      if (invalid_transition_o !== exp_invalid_transition[0]) begin
        $display("[ERROR] cycle=%0d invalid_transition expected %0b got %0b at t=%0t",
                 exp_cycle, exp_invalid_transition[0], invalid_transition_o, $time);
        errors++;
      end

      if (velocity_valid_o !== exp_velocity_valid[0]) begin
        $display("[ERROR] cycle=%0d velocity_valid expected %0b got %0b at t=%0t",
                 exp_cycle, exp_velocity_valid[0], velocity_valid_o, $time);
        errors++;
      end

      if (ab_state_o !== exp_ab_state_vec) begin
        $display("[ERROR] cycle=%0d ab_state expected %0b got %0b at t=%0t",
                 exp_cycle, exp_ab_state_vec, ab_state_o, $time);
        errors++;
      end
    end
  endtask

  initial begin
    $dumpfile("tb_qen_core_file.fst");
    $dumpvars(0, tb_qen_core_file);

    errors     = 0;
    num_vectors = 0;

    enable_i             = 1'b0;
    clear_position_i     = 1'b0;
    clear_error_i        = 1'b0;
    index_reset_enable_i = 1'b0;
    sample_period_i      = '0;
    a_i                  = 1'b0;
    b_i                  = 1'b0;
    z_i                  = 1'b0;

    rst_ni = 1'b0;
    repeat (4) @(posedge clk_i);
    rst_ni = 1'b1;
    @(posedge clk_i);
    #1;

    stim_fd = $fopen("stimuli/stimuli.txt", "r");
    if (stim_fd == 0) begin
      $fatal(1, "[TB] Could not open stimuli/stimuli.txt");
    end

    exp_fd = $fopen("stimuli/expected_response.txt", "r");
    if (exp_fd == 0) begin
      $fatal(1, "[TB] Could not open stimuli/expected_response.txt");
    end

    $display("[TB] Starting QEN file-driven test");

    forever begin
      stim_rc = $fscanf(stim_fd, "%d %d %d %d %d %d %d %d %d\n",
                        stim_cycle,
                        stim_enable,
                        stim_clear_position,
                        stim_clear_error,
                        stim_index_reset_enable,
                        stim_sample_period,
                        stim_a,
                        stim_b,
                        stim_z);

      exp_rc = $fscanf(exp_fd, "%d %d %d %d %d %d %d %d %d %d %d\n",
                       exp_cycle,
                       exp_position,
                       exp_velocity,
                       exp_delta,
                       exp_direction,
                       exp_index_seen,
                       exp_index_position,
                       exp_error_count,
                       exp_invalid_transition,
                       exp_velocity_valid,
                       exp_ab_state);

      if ((stim_rc == -1) && (exp_rc == -1)) begin
        break;
      end

      if (stim_rc != 9) begin
        $fatal(1, "[TB] Bad stimuli line near vector %0d, fscanf returned %0d",
               num_vectors, stim_rc);
      end

      if (exp_rc != 11) begin
        $fatal(1, "[TB] Bad expected line near vector %0d, fscanf returned %0d",
               num_vectors, exp_rc);
      end

      if (stim_cycle != exp_cycle) begin
        $fatal(1, "[TB] Stimulus/expected cycle mismatch: stim=%0d expected=%0d",
               stim_cycle, exp_cycle);
      end

      // Drive each vector on the negative edge so that all inputs are
      // stable before the active positive clock edge. This also makes
      // the waveform easier to interpret: vector N inputs are held
      // cleanly until vector N is checked.
      @(negedge clk_i);

      enable_i             = stim_enable[0];
      clear_position_i     = stim_clear_position[0];
      clear_error_i        = stim_clear_error[0];
      index_reset_enable_i = stim_index_reset_enable[0];
      sample_period_i      = stim_sample_period[SampleWidth-1:0];
      a_i                  = stim_a[0];
      b_i                  = stim_b[0];
      z_i                  = stim_z[0];

      @(posedge clk_i);
      #1;

      check_current();
      num_vectors++;
    end

    $fclose(stim_fd);
    $fclose(exp_fd);

    if (errors == 0) begin
      $display("[TB] QEN core file-driven test PASSED with %0d vectors", num_vectors);
    end else begin
      $display("[TB] QEN core file-driven test FAILED with %0d errors over %0d vectors",
               errors, num_vectors);
      $fatal(1);
    end

    $finish;
  end

endmodule
