#!/bin/bash

# Flag to track if all files pass
all_ok=true

# Loop through all .c files in the src directory
for file in src/*.c; do
    result=$(norminette $file)

    if [[ "$result" == *"OK!"* ]]; then
        echo "$file: OK!"
    else
        echo "$file: ERROR!"
        all_ok=false
    fi
done

for file in libft/*.c; do
    result=$(norminette $file)

    if [[ "$result" == *"OK!"* ]]; then
        echo "$file: OK!"
    else
        echo "$file: ERROR!"
        all_ok=false
    fi
done

# Loop through all .h files in the include directory
for file in include/*.h; do
    result=$(norminette $file)

    if [[ "$result" == *"OK!"* ]]; then
        echo "$file: OK!"
    else
        echo "$file: ERROR!"
        all_ok=false
    fi
done

# Return error code if any file failed
if [ "$all_ok" = false ]; then
    echo "Some files did not pass Norminette checks!"
    exit 1
else
    echo "All files passed Norminette checks!"
    exit 0
fi
