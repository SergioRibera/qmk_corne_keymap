{
  description = "Flake for building vial-qmk firmware";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  # The vial fork of qmk, stores the keyboard config in on-keyboard memory, and
  # supports the `Vial` GUI key map config app.
  inputs.qmk-src = {
    url = "git+https://github.com/qmk/qmk_firmware.git?submodules=1";
    flake = false;
  };

  outputs = { nixpkgs, flake-utils, qmk-src, ... }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };

      preparedQmk = pkgs.runCommand "qmk-with-keymap" {
        nativeBuildInputs = [ pkgs.rsync ];
      } ''
        mkdir -p $out
        rsync -a ${qmk-src}/ $out/
        chmod -R +w $out

        mkdir -p $out/keyboards/crkbd/keymaps/s4rch
        cp -r ${./s4rch}/* $out/keyboards/crkbd/keymaps/s4rch/
      '';

      qmk-build = pkgs.writeShellApplication {
        name = "qmk-build";
        runtimeInputs = with pkgs; [ gnumake ];
        text = ''
          if [ -z "$KEYBOARD" ]; then
            echo "ERROR: KEYBOARD environment variable not set"
            echo "Example: export KEYBOARD=crkbd/rev1"
            exit 1
          fi

          echo "Compiling $KEYBOARD with keymap $KEYMAP ..."
          make -C ${preparedQmk} \
            QMK_HOME=${preparedQmk} \
            BUILD_DIR="$PWD/.build" \
            -j"$(nproc)" \
            "$KEYBOARD":"$KEYMAP"
        '';
      };

      qmk-flash = pkgs.writeShellApplication {
        name = "qmk-flash";
        runtimeInputs = with pkgs; [ gnumake ];
        text = ''
          if [ -z "$KEYBOARD" ]; then
            echo "ERROR: KEYBOARD environment variable not set"
            echo "Example: export KEYBOARD=crkbd/rev1"
            exit 1
          fi

          echo "Flashing $KEYBOARD with keymap $KEYMAP..."
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
          pkgs.qmk
          pkgs.dfu-programmer
          pkgs.dfu-util
          pkgs.avrdude

          pkgs.clang-tools
        ];

        shellHook = ''
          echo ""
          echo "QMK environment is ready!"
          echo ""
          echo "Keyboard set to: crkbd/rev1"
          echo "Keymap set to: s4rch"
          echo ""
          echo "Available Commands:"
          echo "  qmk-build    - Compile firmware"
          echo "  qmk-flash    - Compile and flash"
          echo "  qmk-clean    - Clean build files"
          echo ""
          echo "To change keyboard/keymap:"
          echo "  export KEYBOARD=<new_keyboard>"
          echo "  export KEYMAP=<new_keymap>"
          echo ""
        '';
      };

      apps = {
        default = {
          type = "app";
          program = "${qmk-build}/bin/qmk-build";
        };
        build = {
          type = "app";
          program = "${qmk-build}/bin/qmk-build";
        };
        flash = {
          type = "app";
          program = "${qmk-flash}/bin/qmk-flash";
        };
        clean = {
          type = "app";
          program = "${qmk-clean}/bin/qmk-clean";
        };
      };
    });
}
