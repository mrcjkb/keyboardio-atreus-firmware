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
      kaleidoscope_dir_ready = with import nixpkgs { system = "x86_64-linux"; };
      stdenv.mkDerivation {
        inherit name;
        src = self;
        buildPhase = ''
        '';
        buildInputs = [
          perl
          curl
          arduino-cli
        ];
        installPhase = ''
        mkdir -p "$out/Kaleidoscope"
        cp -R ${kaleidoscope}/* $out/Kaleidoscope
        cd $out/Kaleidoscope
        make setup #FIXME: Currently fails due to attempt to download arduino tools
        '';
      };
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
            KALEIDOSCOPE_DIR = kaleidoscope_dir_ready;
          };
        in
        rec {
          # `nix develop`
          devShell = pkgs.mkShell
            {
              inherit buildInputs nativeBuildInputs;
              shellHook = ''
                export KALEIDOSCOPE_DIR=${kaleidoscope_dir_ready};
              '';
            }// buildEnvVars;
        }
      );
}
