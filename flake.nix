{
  description = "Bridge between HPP and TOPPRA";

  inputs.gepetto.url = "github:gepetto/nix";

  outputs =
    inputs:
    inputs.gepetto.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        overrideAttrs.hpp-toppra =
          { pkgs-final, ... }:
          {
            checkInputs = [ pkgs-final.catch2_3 ];
            doCheck = true;
            src = lib.fileset.toSource {
              root = ./.;
              fileset = lib.fileset.unions [
                ./CMakeLists.txt
                ./include
                ./package.xml
                ./python
                ./src
                ./tests
              ];
            };
          };
      }
    );
}
