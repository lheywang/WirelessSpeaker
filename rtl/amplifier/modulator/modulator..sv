/**
 *  @file   modulator.sv
 *  @brief  Define the PWM modulator, used for the class D control.
 *
 */

module modulator (
    input logic clk,
    input logic rst_n,
    input logic [7:0] control,
    output logic pwm
);

  /*
     * Storages
     */
  logic [7:0] current_control;
  logic [7:0] current_control_inv;
  logic [7:0] counter;

  logic set_pwm;
  logic clr_pwm;

  logic [1:0] mask;

  logic load;

  always_ff @(posedge clk or negedge rst_n) begin : sync_logic

    if (!rst_n) begin
      counter <= 8'b0;
    end else begin
      if ((|counter == 1'b0)) begin
        load <= 1'b1;
      end else begin
        load <= 1'b0;
      end
      counter <= counter + 1;
    end
  end

  always_ff @(posedge clk) begin

    set_pwm <= (!counter[7] && (counter == current_control));
    clr_pwm <= (counter[7] && (counter == current_control_inv));

    if (load) begin
      current_control <= control;
      current_control_inv <= ~control;
    end
  end

  assign mask = {set_pwm, clr_pwm};

  always_ff @(posedge clk) begin

    case (mask)
      2'b00: pwm <= pwm;
      2'b01: pwm <= 1'b0;
      2'b10: pwm <= 1'b1;
      2'b11: pwm <= pwm;

    endcase

  end

endmodule


