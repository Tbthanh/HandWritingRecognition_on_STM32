import os
import csv
import numpy as np
from PIL import Image

# Define paths for input CSV and output folders
csv_file = 'path/to/your_dataset.csv'  # Replace with your CSV file path
output_folder = 'path/to/output_images'  # Replace with your output folder path

# Create folders for each alphabet (A-Z)
for label in range(26):
    label_folder = os.path.join(output_folder, chr(65 + label))  # 65 is ASCII for 'A'
    os.makedirs(label_folder, exist_ok=True)

# Read and process CSV file
with open(csv_file, 'r') as f:
    reader = csv.reader(f)
    next(reader)  # Skip header if there is one
    
    for i, row in enumerate(reader):
        # The last column is assumed to be the label (A, B, C, etc.)
        label = row[-1]
        pixels = np.array(row[:-1], dtype=np.uint8)  # Convert pixels to numpy array
        image_array = pixels.reshape(28, 28)  # Reshape to 28x28
        
        # Save image in corresponding label folder
        image = Image.fromarray(image_array, mode='L')  # 'L' mode for grayscale
        image_path = os.path.join(output_folder, label, f"{label}_{i}.png")
        image.save(image_path)
        
        print(f"Saved {image_path}")

print("CSV to images conversion completed.")
