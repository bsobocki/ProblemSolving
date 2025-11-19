#!/bin/bash

solution_dir_regex="^[0-9]+_.+"

is_solution_dir() {
    local dir="$1"
    [[ -d "$dir" ]] && [[ "$dir" =~ $solution_dir_regex ]]
}

is_test_number_option() {
    local opt="$1"
    [[ "$opt" =~ ^--test=[0-9]+$ ]]
}

# Get all solution directories
mapfile -t all_solution_dirs < <(
    for dir in */; do
        dir="${dir%/}"  # Remove trailing slash
        if is_solution_dir "$dir"; then
            echo "$dir"
        fi
    done
)

solution_dirs=()

if [[ $# -gt 0 ]]; then
    arg="$1"
    
    if is_test_number_option "$arg"; then
        # Extract number from --test=N
        num="${arg#--test=}"
        for sol_dir in "${all_solution_dirs[@]}"; do
            if [[ "$sol_dir" =~ ^${num}_.* ]]; then
                solution_dirs+=("$sol_dir")
            fi
        done
    elif is_solution_dir "$arg"; then
        solution_dirs=("$arg")
    fi
fi

# If no solution dirs found, use all
if [[ ${#solution_dirs[@]} -eq 0 ]]; then
    solution_dirs=("${all_solution_dirs[@]}")
fi

echo "Cleaning old files.."
make clean
echo ""

echo "Solutions:"
echo "----------------------------------------------------------"
printf '%s\n' "${solution_dirs[@]}"
echo "----------------------------------------------------------"

for solution_dir in "${solution_dirs[@]}"; do
    echo ""
    echo "---------------------------------------"
    echo "COMPILE $solution_dir..."
    echo "---------------------------------------"
    if make compile "$solution_dir"; then
        echo "✓ $solution_dir compiled successfully"
    else
        echo "✗ $solution_dir failed"
    fi
done

echo ""
echo ""

for solution_dir in "${solution_dirs[@]}"; do
    echo ""
    echo "---------------------------------------"
    echo "RUN TESTS: $solution_dir..."
    echo "---------------------------------------"
    make run "$solution_dir"
done
