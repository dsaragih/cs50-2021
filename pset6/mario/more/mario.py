from cs50 import get_int

while True:
    height = get_int("height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    # Prints the spaces on the left
    for j in range(height - i - 1):
        print(" ", end='')
        
    # Prints the left pyramid
    for k in range(i + 1):
        print("#", end='')
        
    # Prints the gap b/w the 2 pyramids
    print("  ", end='')
    
    # Prints the right pyramid
    for l in range(i + 1):
        print("#", end='')
        
    # Brings printer down to next level
    print("")