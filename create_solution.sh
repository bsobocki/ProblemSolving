solution_name=$1

solution_regex="[0-9]+_.+"

max_solution_number=$(ls | grep -E $solution_regex | sed -E 's/([0-9+])_.+/\1/g' | sort -nr | head -n1)

new_solution_number=$((max_solution_number + 1))

solution_dir=${new_solution_number}_$solution_name

mkdir $solution_dir
cp utils/solution_template.cpp $solution_dir/solution.cpp
cp utils/description_template.md $solution_dir/description.md