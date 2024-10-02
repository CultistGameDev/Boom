{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };


  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem ({ pkgs }: {
  	nativeBuildInputs = with pkgs; [
	    pkg-config
	    clang
	    clang-tools

	    xorg.libX11
	    xorg.libXrandr
	    xorg.libXinerama
	    xorg.libXcursor
	    xorg.libXi
	];
        default = pkgs.mkShell.override
	  {

	  }
	  {
	  packages = with pkgs; [
      cmake
      gnumake
	    glfw
	  ] ++ (if system == "aarch64-darwiu" then [] else [gdb]);
	  };
      });
    };
}
