#!/bin/bash

solution_dir_regex="^[0-9]+_.+"
solutions_root_dir="./solutions"

is_solution_dir() {
    local dir="$1"
    local path="$solutions_root_dir/$dir"
    [[ -d "$path" ]] && [[ "$dir" =~ $solution_dir_regex ]]
}

is_test_number_option() {
    local opt="$1"
    [[ "$opt" =~ ^--test=[0-9]+$ ]]
}

# Get all solution directories
mapfile -t all_solution_dir_names < <(
    for dir in solutions/*/; do
        dir="$(basename "${dir%/}")"  # Get only dir name with removed trailing slash
        if is_solution_dir "$dir"; then
            echo "$dir"
        fi
    done
)

solution_dir_names=()

if [[ $# -gt 0 ]]; then
    arg="$1"
    
    if is_test_number_option "$arg"; then
        # Extract number from --test=N
        num="${arg#--test=}"
        for sol_dir in "${all_solution_dir_names[@]}"; do
            if [[ "$sol_dir" =~ ^${num}_.* ]]; then
                solution_dir_names+=("$sol_dir")
            fi
        done
    elif is_solution_dir "$arg"; then
        solution_dir_names=("$arg")
    fi
fi

# If no solution dirs found, use all
if [[ ${#solution_dir_names[@]} -eq 0 ]]; then
    solution_dir_names=("${all_solution_dir_names[@]}")
fi

echo "Cleaning old files.."
make clean
echo ""

echo "Solutions:"
echo "----------------------------------------------------------"
printf '%s\n' "${solution_dir_names[@]}"
echo "----------------------------------------------------------"

for solution_dir_name in "${solution_dir_names[@]}"; do
    solution_dir=$solutions_root_dir/$solution_dir_name
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

for solution_dir in "${solution_dir_names[@]}"; do
    solution_dir=$solutions_root_dir/$solution_dir
    echo ""
    echo "---------------------------------------"
    echo "RUN TESTS: $solution_dir..."
    echo "---------------------------------------"
    make run "$solution_dir"
done
