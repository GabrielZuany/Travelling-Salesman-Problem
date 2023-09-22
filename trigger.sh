# run randon.py
# run make rand
# run profiler.py

echo "Running trigger.sh"
echo "Running random.py"
python ./RandomInputs/rand.py

echo "Running make rand"
make read_test

echo "Running main..."
for file in ./RandomInputs/*.tsp
do
    echo "Running $file"
    ./main $file
done

echo "Running profiler.py"
python ./Profiler/profiler.py
