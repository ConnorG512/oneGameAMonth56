{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
    lib = nixpkgs.lib;
  in 
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [ 
        clang-tools
        sdl3.dev
        sdl3-image.dev
        sdl3-ttf
        lua

        gef
        strace
      ];

      shellHook = ''
        echo "Entering One Game A Month #56 shell!"
      '';
    };
    
    debug = pkgs.stdenv.mkDerivation (finalAttrs: {
      pname = "oneGameAMonth";
      version = "debug";
      src = ./.;

      dontStrip = true;

      cmakeFlags = [
        "-DCMAKE_BUILD_TYPE=Debug"
      ];

      nativeBuildInputs = with pkgs; [
        makeWrapper
        cmake 
        ninja
        pkg-config
        
      ];
      buildInputs = with pkgs; [
        sdl3
        sdl3-image
        sdl3-ttf
        mesa
        
        lua
      ];
      
      # Missing libGL.so.1 runtime error. Wrapping to fix
      postFixup = ''
        wrapProgram $out/bin/oneGameAMonth \
          --set LD_LIBRARY_PATH ${lib.makeLibraryPath [
            pkgs.libGL.out
            pkgs.mesa
            pkgs.alsa-lib
          ]} \
          --set SDL_AUDIODRIVER=alsa
      '';
    });
    
    release = pkgs.stdenv.mkDerivation (finalAttrs: {
      pname = "oneGameAMonth";
      version = "debug";
      src = ./.;

      dontStrip = true;

      cmakeFlags = [
        "-DCMAKE_BUILD_TYPE=Release"
      ];

      nativeBuildInputs = with pkgs; [
        cmake 
        ninja
        pkg-config
        
      ];
      buildInputs = with pkgs; [
        sdl3
        sdl3-image
        sdl3-ttf
        mesa
        
        lua
      ];
    });
  };
}
