{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
    pkgsMingw = pkgs.pkgsCross.mingwW64;
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
        cmake 
        ninja
        pkg-config
        makeWrapper
      ];
      buildInputs = with pkgs; [
        sdl3
        sdl3-image
        sdl3-ttf
        mesa
        
        lua
      ];
      postFixup = 
      let
        libs = with pkgs; [
          libGL.out
          mesa
        ];
      in
      ''
        wrapProgram $out/bin/oneGameAMonth \
          --set LD_LIBRARY_PATH ${lib.makeLibraryPath libs}
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

    mingw =
    let 
      sdl3-image = pkgsMingw.stdenv.mkDerivation {
        pname = "sdl3-image";
        version = "release";
        src = pkgsMingw.fetchzip {
          url = "https://github.com/libsdl-org/SDL_image/releases/download/release-3.4.0/SDL3_image-devel-3.4.0-mingw.zip";
          hash = "sha256-nCkWP03qRN2OOzYEDZ4HKcnsrW4RV1+G2+b9JUXZDas=";
        };
        dontConfigure = true;
        dontBuild = true;

        installPhase = ''
          runHook preInstall
          mkdir -p $out
          cp -rv x86_64-w64-mingw32/* $out/
          runHook postInstall
        '';
      };
      
      sdl3-ttf = pkgsMingw.stdenv.mkDerivation {
        pname = "sdl3-image";
        version = "release";
        src = pkgsMingw.fetchzip {
          url = "https://github.com/libsdl-org/SDL_ttf/releases/download/release-3.2.2/SDL3_ttf-devel-3.2.2-mingw.tar.gz";
          hash = "sha256-hmfypcP+myh4tRvsMskz9/V1/RGizugfeoHj6vkY46E=";
        };
        dontConfigure = true;
        dontBuild = true;

        installPhase = ''
          runHook preInstall
          mkdir -p $out
          cp -rv x86_64-w64-mingw32/* $out/
          runHook postInstall
        '';
        };

        lua = pkgsMingw.stdenv.mkDerivation {
          pname = "lua";
          version = "5.4.8";
          src = pkgsMingw.fetchurl {
            url = "https://mirror.msys2.org/mingw/mingw64/mingw-w64-x86_64-lua-5.4.8-1-any.pkg.tar.zst";
            hash = "sha256-0p8AwpzrYHGB/8MZ1E4Edu6TYFde+gXGglkLB6a+yNE=";
          };
          nativeBuildInputs = [
            pkgs.zstd
          ];

          installPhase = ''
            runHook preInstall
            mkdir -p $out
            cp -rv . "$out/"
            runHook postInstall
          '';
        };
    in 
    pkgsMingw.stdenv.mkDerivation (finalAttrs: {
      pname = "oneGameAMonth";
      version = "mingw";
      src = ./.;

      nativeBuildInputs = [
        pkgs.cmake 
        pkgs.ninja
        pkgs.pkg-config
        pkgs.zstd
      ];
      buildInputs = [
        pkgsMingw.sdl3
        lua
        sdl3-ttf
        sdl3-image
      ];

      installPhase = ''
        mkdir -p $out/bin/
        cp oneGameAMonth.exe $out/bin/
        cp -r $src/assets $out/bin
        cp -r $src/gamescript $out/bin
        cp $src/config.lua $out/bin
        find . -name "*.dll" -exec cp {} $out/bin/ \;
     '';
    });
  };
}
