{
  description = "Flake for building QMK firmware for crkbd/s4rch";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  inputs.keymap-drawer = {
    url = "github:caksoylar/keymap-drawer";
    flake = false;
  };

  inputs.qmk-src = {
    url = "git+https://github.com/qmk/qmk_firmware.git?submodules=1";
    flake = false;
  };

  outputs = { nixpkgs, flake-utils, keymap-drawer, qmk-src, ... }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
      python = pkgs.python3;
      pythonPkgs = python.pkgs;

      tree-sitter-devicetree = pythonPkgs.buildPythonPackage rec {
        pname = "tree_sitter_devicetree";
        version = "0.14.1";
        pyproject = true;
        build-system = [ pythonPkgs.setuptools ];
        src = pythonPkgs.fetchPypi {
          inherit pname version;
          sha256 = "2584a68a01ca75abb8da6020dce3d9e8c77504fa492bbac95d1c76e8d4bf83a2";
        };
        doCheck = false;
      };

      keymap-drawer-app = pythonPkgs.buildPythonApplication {
        pname = "keymap-drawer";
        version = "unstable";
        src = keymap-drawer;
        format = "pyproject";
        nativeBuildInputs = [ pythonPkgs.poetry-core ];
        propagatedBuildInputs = with pythonPkgs; [
          pydantic
          pydantic-settings
          pcpp
          pyyaml
          platformdirs
          tree-sitter
          tree-sitter-devicetree
          pyparsing
        ];
        doCheck = false;
      };

      preparedQmk = pkgs.runCommand "qmk-with-keymap" { } ''
        mkdir -p $out
        cp -r ${qmk-src}/. $out/
        chmod -R u+w $out
        mkdir -p $out/keyboards/crkbd/keymaps/s4rch
        cp -r ${./s4rch}/. $out/keyboards/crkbd/keymaps/s4rch/
      '';

      generate-svg = pkgs.writeShellApplication {
        name = "generate-keymap-svg";
        runtimeInputs = [
          pkgs.qmk
          keymap-drawer-app
          pkgs.coreutils
        ];
        text = ''
          set -euo pipefail

          out_dir="''${OUT_DIR:-$PWD}"
          out_svg="$out_dir/.github/keymap.svg"
          tmp="$(mktemp -d)"
          trap 'rm -rf "$tmp"' EXIT

          export QMK_HOME="${preparedQmk}"

          echo "==> qmk c2json (kb=crkbd/rev1 km=s4rch)"
          (cd "$QMK_HOME" && qmk c2json -kb crkbd/rev1 -km s4rch -o "$tmp/keymap.json")

          echo "==> keymap parse"
          keymap parse \
            -c 10 \
            -l Base Lower Raise Minecraft Adjust \
            -q "$tmp/keymap.json" \
            > "$tmp/keymap.yaml"

          echo "==> keymap draw"
          keymap draw "$tmp/keymap.yaml" -o "$out_svg"

          echo "OK: $out_svg"
        '';
      };

      qmk-build = pkgs.writeShellApplication {
        name = "qmk-build";
        runtimeInputs = [ pkgs.gnumake ];
        text = ''
          set -euo pipefail
          KEYBOARD="''${KEYBOARD:-crkbd/rev1}"
          KEYMAP="''${KEYMAP:-s4rch}"

          echo "Compiling $KEYBOARD:$KEYMAP..."
          make -C ${preparedQmk} \
            QMK_HOME=${preparedQmk} \
            BUILD_DIR="$PWD/.build" \
            -j"$(nproc)" \
            "$KEYBOARD":"$KEYMAP"
        '';
      };

      qmk-flash = pkgs.writeShellApplication {
        name = "qmk-flash";
        runtimeInputs = [ pkgs.gnumake ];
        text = ''
          set -euo pipefail
          KEYBOARD="''${KEYBOARD:-crkbd/rev1}"
          KEYMAP="''${KEYMAP:-s4rch}"

          echo "Flashing $KEYBOARD:$KEYMAP..."
          make -C ${preparedQmk} \
            QMK_HOME=${preparedQmk} \
            BUILD_DIR="$PWD/.build" \
            -j"$(nproc)" \
            "$KEYBOARD":"$KEYMAP":flash
        '';
      };

      qmk-clean = pkgs.writeShellApplication {
        name = "qmk-clean";
        text = ''
          echo "Cleaning build directory..."
          rm -rf "$PWD/.build"
        '';
      };

    in
    {
      devShells.default = pkgs.mkShell {
        KEYBOARD = "crkbd/rev1";
        KEYMAP = "s4rch";

        buildInputs = [
          qmk-build
          qmk-flash
          qmk-clean
          generate-svg
          pkgs.qmk
          pkgs.dfu-programmer
          pkgs.dfu-util
          pkgs.avrdude
          python
          keymap-drawer-app
          pkgs.clang-tools
        ];

        shellHook = ''
          echo ""
          echo "QMK environment is ready!"
          echo ""
          echo "Keyboard: $KEYBOARD"
          echo "Keymap:   $KEYMAP"
          echo ""
          echo "Commands:"
          echo "  qmk-build           - Compile firmware"
          echo "  qmk-flash           - Compile and flash"
          echo "  qmk-clean           - Clean build files"
          echo "  generate-keymap-svg - Generate keymap.svg from keymap.c"
          echo ""
        '';
      };

      apps = {
        default = { type = "app"; program = "${qmk-build}/bin/qmk-build"; };
        build   = { type = "app"; program = "${qmk-build}/bin/qmk-build"; };
        flash   = { type = "app"; program = "${qmk-flash}/bin/qmk-flash"; };
        clean   = { type = "app"; program = "${qmk-clean}/bin/qmk-clean"; };
        svg     = { type = "app"; program = "${generate-svg}/bin/generate-keymap-svg"; };
      };
    });
}
