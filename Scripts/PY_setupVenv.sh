
GREEN='\033[0;32m' 
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e $GREEN
echo ------
echo -e "=======| Configurando Ambiente de Desenvolvimento Virtual Python |======="
echo -e ----- 
echo "=========================| Instalando Python3 |============================="
echo -e ----- $NC 

sudo apt install python3-venv
sudo apt install python3-pip

echo -e $GREEN -----
echo "==============| Criando Ambiente de Desenvolvimento Virtual Python |=========="
echo -e ----- $NC

python3 -m venv .VirtualEnvironment

echo -e $GREEN -----
echo "==============| Ativando Ambiente de Desenvolvimento Virtual Python |=========="
echo -e ----- $NC

chmod +x .VirtualEnvironment/bin/activate
source .VirtualEnvironment/bin/activate

echo -e $GREEN -----
echo "=====================| Instalando Dependências do Projeto |===================="
echo -e ----- $NC

pip install -r Scripts/requirements.txt

echo -e $GREEN -----
echo Ambiente de Desenvolvimento Virtual Python configurado com sucesso!
echo -e ----- $NC

echo -e $BLUE Iniciando Visual Studio Code... $NC
code .