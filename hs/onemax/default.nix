{ mkDerivation, base, random, stdenv }:
mkDerivation {
  pname = "onemax";
  version = "0.1.0.0";
  src = ./.;
  isLibrary = false;
  isExecutable = true;
  executableHaskellDepends = [ base random ];
  license = "unknown";
  hydraPlatforms = stdenv.lib.platforms.none;
}
