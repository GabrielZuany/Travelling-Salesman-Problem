GREEN='\033[0;32m' 
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e $GREEN -----
echo "==============| Ativando Ambiente de Desenvolvimento Virtual Python |=========="
echo -e ----- $NC

source venv/bin/activate

echo -e $BLUE Iniciando Visual Studio Code... $NC
code .