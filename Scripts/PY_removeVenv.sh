GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e $RED "=> Desativando Ambiente de Desenvolvimento Virtual Python..."
deactivate

echo -e $RED "=> Removendo Ambiente de Desenvolvimento Virtual Python..."
rm -rf .VirtualEnvironment

echo -e $GREEN "=> Ambiente de Desenvolvimento Virtual Python removido com sucesso!"