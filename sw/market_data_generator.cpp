/* This program generates an order book of UDP ITCH protocol orders.
 * The first 100 orders are pre-defined buy and sell orders around
 * a mid-price of 100. The remaining orders are generated randomly.
 * All orders are written to a binary file, where each line represents
 * an order in the ITCH protocol format, consecutively where the first
 * line is the first order, the second line is the second order, and so on.
 */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <algorithm>
using namespace std;

// ITCH UDP Protocol Structure
#pragma pack(push, 1) // Ensure no padding between struct members
struct ITCH_Order {
    uint8_t  message_type;           // 1 Byte  
    uint16_t stock_locate;           // 2 Bytes
    uint16_t tracking_number;        // 2 Bytes
    uint8_t  timestamp[6];           // 6 Bytes
    uint64_t order_reference_number; // 8 Bytes
    uint8_t  buy_sell_indicator;     // 1 Byte
    uint32_t shares;                 // 4 Bytes
    uint64_t stock;                  // 8 Bytes
    uint32_t price;                  // 4 Bytes
};
#pragma pack(pop) // End of struct packing

int main() {
    const int starting_price = 1000000; // Mid-price in ITCH protocol format (e.g., 100.00 is represented as 1000000)
    const int diff = 100;               // Price difference in ITCH protocol format (0.01 is represented as 100)
    
    uint64_t   sim_time_ns;             // Time passed since midnight in nanoseconds
    int        reference_number;        // Order number
    ITCH_Order order;                   // Create an instance of the ITCH_Order struct

    // Open binary file
    ofstream bin_file("../results/generated_order_book.bin");
    if (!bin_file.is_open()) {
        cerr << "Error: Could not open binary file." << endl;
        return 1;
    }

    sim_time_ns = 34'200'000'000'000;   // 9:30 AM (NASDAQ opens)
    reference_number = 1;

    // Generate buy orders around the mid-price
    for (int i = 0; i < 50; i++) {
        order.message_type       = 0x41;         // 'A' for add order
        order.stock_locate       = __builtin_bswap16(0x00'01);
        order.tracking_number    = __builtin_bswap16(0x00'00);
        memcpy(order.timestamp, &sim_time_ns, 6);
        reverse(begin(order.timestamp), end(order.timestamp));
        order.order_reference_number = __builtin_bswap64(reference_number);
        order.buy_sell_indicator = 0x42;         // 'B' for buy order
        order.shares             = __builtin_bswap32(100);
        order.stock              = __builtin_bswap64(0x41'41'50'4C'20'20'20'20); // "AAPL    "
        order.price              = __builtin_bswap32(starting_price - (i + 1) * diff);

        bin_file.write(reinterpret_cast<const char*>(&order), sizeof(order));

        reference_number++;
    }

    // Generate sell orders around the mid price
    for (int i = 0; i < 50; i++) {
        order.message_type       = 0x41;         // 'A' for add order
        order.stock_locate       = __builtin_bswap16(0x00'01);
        order.tracking_number    = __builtin_bswap16(0x00'00);
        memcpy(order.timestamp, &sim_time_ns, 6);
        reverse(begin(order.timestamp), end(order.timestamp));
        order.order_reference_number = __builtin_bswap64(reference_number);
        order.buy_sell_indicator = 0x53;         // 'S' for sell order
        order.shares             = __builtin_bswap32(100);
        order.stock              = __builtin_bswap64(0x41'41'50'4C'20'20'20'20); // "AAPL    "
        order.price              = __builtin_bswap32(starting_price + (i + 1) * diff);

        bin_file.write(reinterpret_cast<const char*>(&order), sizeof(order));

        reference_number++;
    }
}