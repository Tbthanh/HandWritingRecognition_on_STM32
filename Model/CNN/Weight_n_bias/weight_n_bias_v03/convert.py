import os

def reformat_file(input_path, output_path):
    # Reads the input file, processes the content, and writes it to the output file
    with open(input_path, 'r') as infile, open(output_path, 'w') as outfile:
        data = infile.read().strip()
        numbers = data.split(', ')
        
        # Write 3 numbers per line with a tab at the beginning
        for i in range(0, len(numbers), 3):
            line = "\t" + ", ".join(numbers[i:i+3]) + ",\n"
            outfile.write(line)

def batch_reformat(input_dir, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for filename in os.listdir(input_dir):
        input_path = os.path.join(input_dir, filename)
        output_path = os.path.join(output_dir, filename)
        
        # Skip directories, only process files
        if os.path.isfile(input_path):
            reformat_file(input_path, output_path)
            print(f"Processed: {input_path} -> {output_path}")

# Define input and output directories
input_dir = 'raw'
output_dir = 'converted'

# Run batch processing
batch_reformat(input_dir, output_dir)
