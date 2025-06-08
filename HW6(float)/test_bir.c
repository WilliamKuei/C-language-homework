#include <stdio.h>
#include <stdint.h>

// Function prototypes
void print_binary(uint8_t num);
void set_bit_demo();
void clear_bit_demo();
void rightmost_bit_demo();
void count_bits_demo();

int main() {
    printf("=== Bit Manipulation Demonstration ===\n\n");
    
    set_bit_demo();
    clear_bit_demo();
    rightmost_bit_demo();
    count_bits_demo();
    
    return 0;
}

// Helper function: Print number in binary format
void print_binary(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

// Set bit demonstration
void set_bit_demo() {
    printf("\n1. Setting a Bit:\n");
    
    uint8_t ft = 0b00000000;  // Initial value
    int i = 3;                // Bit position to set
    
    printf("Original value: ");
    print_binary(ft);
    printf(" (0x%02X)\n", ft);
    
    uint8_t BM = (0x01) << i;  // Create bitmask
    ft = ft | BM;              // Set the bit
    
    printf("After setting bit %d: ", i);
    print_binary(ft);
    printf(" (0x%02X)\n", ft);
}

// Clear bit demonstration
void clear_bit_demo() {
    printf("\n2. Clearing a Bit:\n");
    
    uint8_t ft = 0b00001000;  // Initial value (bit 3 is set)
    int i = 3;                // Bit position to clear
    
    printf("Original value: ");
    print_binary(ft);
    printf(" (0x%02X)\n", ft);
    
    uint8_t BM = (0x01) << i;  // Create bitmask
    ft = ft & (~BM);           // Clear the bit
    
    printf("After clearing bit %d: ", i);
    print_binary(ft);
    printf(" (0x%02X)\n", ft);
}

// Find rightmost set bit demonstration
void rightmost_bit_demo() {
    printf("\n3. Finding Rightmost Set Bit:\n");
    
    uint8_t a = 0b00101100;  // Example value
    uint8_t b;
    
    printf("a = ");
    print_binary(a);
    printf(" (0x%02X)\n", a);
    
    b = a & (a ^ (a - 1));  // Isolate rightmost set bit
    
    printf("Rightmost set bit: ");
    print_binary(b);
    printf(" (0x%02X)\n", b);
}

// Count set bits demonstration
void count_bits_demo() {
    printf("\n4. Counting Set Bits:\n");
    
    uint8_t c = 0b10110110;  // Example value (5 bits set)
    uint8_t d;
    
    printf("c = ");
    print_binary(c);
    printf(" (0x%02X)\n", c);
    
    // Parallel counting algorithm
    d = (c & 0x55) + ((c & 0xAA) >> 1);
    d = (d & 0x33) + ((d & 0xCC) >> 2);
    d = (d & 0x0F) + ((d & 0xF0) >> 4);
    
    printf("Number of set bits: %d\n", d);
}