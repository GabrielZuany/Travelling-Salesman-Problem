echo "Running trigger.sh"
echo "Running random.py"
python3 "RandomInputs/rand.py"

echo "Running make rand"
make read_test

for file in ./Others/exemplos/exemplos/in/*.tsp
do
    echo "Running $file"
    ./trab1 $file
done

echo "Running main..."
for file in ./RandomInputs/*.tsp
do
    echo "Running $file"
    ./trab1 $file
done

echo "Running profiler.py"
python3 ./Profiler/profiler.py
