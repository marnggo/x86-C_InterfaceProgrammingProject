import random
import sys

def generate_input(num_cars, output_file=None):
    """
    Generate random test input for the car acceleration program.
    
    Parameters:
    - num_cars: Number of cars (rows) to generate
    - output_file: Optional filename to write output (if None, prints to stdout)
    """
    
    lines = []
    
    # First line: number of cars
    lines.append(str(num_cars))
    
    # Generate random data for each car
    for i in range(num_cars):
        # Initial velocity: 0-100 KM/H
        vi = random.uniform(0.0, 100.0)
        
        # Final velocity: 50-200 KM/H (typically higher than initial)
        vf = random.uniform(50.0, 200.0)
        
        # Time: 1-15 seconds
        t = random.uniform(1.0, 15.0)
        
        # Format with 1 decimal place and commas
        lines.append(f"{vi:.1f}, {vf:.1f}, {t:.1f}")
    
    # Output
    output = '\n'.join(lines)
    
    if output_file:
        with open(output_file, 'w') as f:
            f.write(output)
        print(f"Generated {num_cars} test cases in '{output_file}'")
    else:
        print(output)

def main():
    # Check command line arguments
    if len(sys.argv) < 2:
        print("Usage: python generate_input.py <num_cars> [output_file]")
        print("\nExamples:")
        print("  python generate_input.py 10                    # Print to console")
        print("  python generate_input.py 100 input_100.txt     # Save to file")
        print("  python generate_input.py 10000 > input.txt     # Redirect to file")
        sys.exit(1)
    
    num_cars = int(sys.argv[1])
    output_file = sys.argv[2] if len(sys.argv) > 2 else None
    
    generate_input(num_cars, output_file)

if __name__ == "__main__":
    main()