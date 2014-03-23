rm -rf dist
mkdir -p dist
export OKRA_HOME=$(cd ..; pwd)
export LD_LIBRARY_PATH=$OKRA_HOME/dist/bin:$LD_LIBRARY_PATH
./buildone.sh Squares
