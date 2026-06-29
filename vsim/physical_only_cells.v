// Empty simulation models for physical-only cells in the final OpenROAD netlist.
// These cells have no functional behavior; they are only for layout/well/density/pad landing.

`celldefine

module FILLER1  (); endmodule
module FILLER2  (); endmodule
module FILLER4  (); endmodule
module FILLER8  (); endmodule
module FILLER16 (); endmodule
module FILLER32 (); endmodule
module FILLER64 (); endmodule

module WELLTAP (); endmodule

// OpenROAD final netlist uses this ETH/IHP bondpad name.
module bondpad5l_70x70 (pad);
  inout pad;
endmodule

`endcelldefine
