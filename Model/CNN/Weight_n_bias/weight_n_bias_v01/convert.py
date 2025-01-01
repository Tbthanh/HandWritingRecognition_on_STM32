def reformat_file(input_file, output_file):
    with open(input_file, 'r') as infile:
        # Read the input file and split into floats
        data = infile.read().strip().split(',')

    # Remove any leading or trailing whitespace from each number
    data = [num.strip() for num in data]

    # Reformat the numbers into rows of 3, each prefixed with a tab
    formatted_lines = []
    for i in range(0, len(data), 3):
        line = "\t" + ", ".join(data[i:i+3]) + ","
        formatted_lines.append(line)

    # Join all lines with a newline
    formatted_content = "\n".join(formatted_lines)

    with open(output_file, 'w') as outfile:
        # Write the formatted content to the output file
        outfile.write(formatted_content)

# Example usage
input_path = 'raw/conv3_weight.txt'
output_path = 'converted/conv3_weight.txt'
reformat_file(input_path, output_path)
