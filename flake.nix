{
  description = "...";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
    kaleidoscope = {
      url = "github:keyboardio/Kaleidoscope";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, utils, kaleidoscope, ... }:
    let
      name = "keyboardio-atreus-firmware";
    in
    utils.lib.eachDefaultSystem
      (system:
        let
          # Imports
          pkgs = import nixpkgs {
            inherit system;
            # overlays = [
            # ];
          };

          # Configuration for the non-Rust dependencies
          buildInputs = with pkgs; [ 
            kaleidoscope
          ];
          nativeBuildInputs = with pkgs; [ 
            gcc 
            gnumake 
          ];
          buildEnvVars = {
            KALEIDOSCOPE_DIR = kaleidoscope;
          };
        in
        rec {
          # `nix develop`
          devShell = pkgs.mkShell
            {
              inherit buildInputs nativeBuildInputs;
              shellHook = ''
                export KALEIDOSCOPE_DIR=${kaleidoscope};
              '';
            }// buildEnvVars;
        }
      );
}
