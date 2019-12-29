{ pkgs ? import <nixpkgs> {} }:

with pkgs;

stdenv.mkDerivation {
  name = "commands-nix";

  buildInputs = [ yarn reason ];

  shellHook = ''
    export PATH=~/bin:$PATH
  '';
}
