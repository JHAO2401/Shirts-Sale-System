# Shirts-Sale-System

A C++ console-based clothing sales system (**LongDay Store**). Customers can browse apparel items, add them to a cart, apply discounts, choose delivery or pick-up, pay by e-Wallet / credit card / debit card / cash, and receive an invoice and receipt. Staff can view customer records and company sales reports.

## Features

- **Product catalog**: Skirt, Dress, T-shirt, Pants, Outwear, Jeans with sizes (S/M/L/XL) and prices in RM.
- **Shopping cart**: add items, view cart, delete items or clear the cart.
- **Pricing & discounts**: tiered discounts based on subtotal, plus service charge (4%) and tax (3%), with optional delivery fee (RM 5).
- **Delivery / pick-up**: enter delivery address and phone number for delivery orders.
- **Payment methods**: e-Wallet, Credit Card, Debit Card, Cash (with change calculation).
- **Invoice & receipt**: printed invoice before payment and receipt after payment.
- **Reports**: customer records and company report (total revenue, total items sold).

## Tech Stack

- C++ (standard library: `<iostream>`, `<string>`, `<iomanip>`, `<cctype>`, `<cstdlib>`)
- Windows API (`<windows.h>` for `Sleep` and `system("cls")`)
- Compiled with a C++ compiler (e.g., MinGW / g++ on Windows)

## Project Structure

```
LongDay.C++   # Main source file (single-file console application)
LongDay.exe   # Compiled executable (ignored by .gitignore — not committed)
```

## Getting Started

### Compile

Using MinGW/g++:

```bash
g++ LongDay.C++ -o LongDay.exe
```

Or use any C++ compiler to build `LongDay.C++`.

### Run

```bash
./LongDay.exe
```

Or double-click `LongDay.exe` on Windows.

## Usage

1. Run the program and select from the main menu:
   - **1. Order entry** — enter customer name, add items to cart, adjust quantities, choose delivery/pick-up, pay, and print receipt.
   - **2. Reporting** — view customer records and company sales report.
   - **3. Exit** — quit the program.

## Notes

- Currency is displayed in **RM** (Malaysian Ringgit).
- The program is single-file and uses in-memory storage (data resets when the program exits).
