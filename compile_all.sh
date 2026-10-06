#!/bin/bash
# ─────────────────────────────────────────────────────────────
#  Compile All Lab Programs
#  Usage: bash compile_all.sh
# ─────────────────────────────────────────────────────────────

BASE="$(dirname "$0")"
PASS=0; FAIL=0

compile() {
    local dir="$1"
    local src="$2"
    local out="$3"
    if gcc -o "$BASE/$dir/$out" "$BASE/$dir/$src" 2>/dev/null; then
        echo "  [OK]  $dir/$src"
        PASS=$((PASS+1))
    else
        echo "  [FAIL] $dir/$src"
        FAIL=$((FAIL+1))
        gcc -o "$BASE/$dir/$out" "$BASE/$dir/$src"
    fi
}

echo "=== Compiling Q1 Matrix (TCP) ==="
compile q1_matrix/tcp server.c server
compile q1_matrix/tcp client.c client

echo "=== Compiling Q1 Matrix (UDP) ==="
compile q1_matrix/udp server.c server
compile q1_matrix/udp client.c client

echo "=== Compiling Q1 Matrix Addition (TCP) ==="
compile q1_matrix_addition/tcp server.c server
compile q1_matrix_addition/tcp client.c client

echo "=== Compiling Q1 Matrix Addition (UDP) ==="
compile q1_matrix_addition/udp server.c server
compile q1_matrix_addition/udp client.c client

echo "=== Compiling Q2 Multichat (TCP) ==="
compile q2_multichat/tcp server.c server
compile q2_multichat/tcp client.c client

echo "=== Compiling Q3 DateTime (TCP) ==="
compile q3_datetime/tcp server.c server
compile q3_datetime/tcp client.c client

echo "=== Compiling Q3 DateTime (UDP) ==="
compile q3_datetime/udp server.c server
compile q3_datetime/udp client.c client

echo "=== Compiling Q4 Abbreviation (UDP) ==="
compile q4_abbreviation/udp server.c server
compile q4_abbreviation/udp client.c client

echo "=== Compiling Q5 Fibonacci (TCP) ==="
compile q5_fibonacci/tcp server.c server
compile q5_fibonacci/tcp client.c client

echo "=== Compiling Q5 Fibonacci (UDP) ==="
compile q5_fibonacci/udp server.c server
compile q5_fibonacci/udp client.c client

echo "=== Compiling Q6 Palindrome (TCP) ==="
compile q6_palindrome/tcp server.c server
compile q6_palindrome/tcp client.c client

echo "=== Compiling Q6 Palindrome (UDP) ==="
compile q6_palindrome/udp server.c server
compile q6_palindrome/udp client.c client

echo "=== Compiling Q7 Prime (TCP) ==="
compile q7_prime/tcp server.c server
compile q7_prime/tcp client.c client

echo "=== Compiling Q7 Prime (UDP) ==="
compile q7_prime/udp server.c server
compile q7_prime/udp client.c client

echo "=== Compiling Q8 Odd/Even (TCP) ==="
compile q8_oddeven/tcp server.c server
compile q8_oddeven/tcp client.c client

echo "=== Compiling Q8 Odd/Even (UDP) ==="
compile q8_oddeven/udp server.c server
compile q8_oddeven/udp client.c client

echo "=== Compiling Q9 Average (TCP) ==="
compile q9_average/tcp server.c server
compile q9_average/tcp client.c client

echo "=== Compiling Q9 Average (UDP) ==="
compile q9_average/udp server.c server
compile q9_average/udp client.c client

echo "=== Compiling Q10 Sum of N (TCP) ==="
compile q10_sumnumbers/tcp server.c server
compile q10_sumnumbers/tcp client.c client

echo "=== Compiling Q10 Sum of N (UDP) ==="
compile q10_sumnumbers/udp server.c server
compile q10_sumnumbers/udp client.c client

echo "=== Compiling Q11 String Reverse (TCP) ==="
compile q11_stringreverse/tcp server.c server
compile q11_stringreverse/tcp client.c client

echo "=== Compiling Q11 String Reverse (UDP) ==="
compile q11_stringreverse/udp server.c server
compile q11_stringreverse/udp client.c client

echo "=== Compiling Q12 Factorial (TCP) ==="
compile q12_factorial/tcp server.c server
compile q12_factorial/tcp client.c client

echo "=== Compiling Q12 Factorial (UDP) ==="
compile q12_factorial/udp server.c server
compile q12_factorial/udp client.c client

echo ""
echo "─────────────────────────────────"
echo "  PASSED: $PASS    FAILED: $FAIL"
echo "─────────────────────────────────"
