{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Já inclusos no stdenv:
    # gcc
    # gnumake
  ];
  packages = with pkgs; [
    zip
  ];
}
