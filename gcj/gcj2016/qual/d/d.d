#!/usr/bin/rdmd

// $ dmd d.d
// $ ./d < input_file

import std.stdio;
import std.array;
import std.string;
import std.conv;
import std.file;
import std.bigint;

BigInt power(BigInt base, BigInt n) {
    BigInt ret = 1;
    while(n > 0) {
        ret *= base;
        n--;
    }
    return ret;
}

void solve(int tc) {
    auto items = readln.split;
    BigInt K = BigInt(items[0].to!int);
    BigInt C = BigInt(items[1].to!int);
    BigInt S = BigInt(items[2].to!int);

    BigInt minimum = (K + C - 1) / C;
    if (S < minimum) {
        writeln(" IMPOSSIBLE");
        return;
    }

    BigInt[] ans;
    BigInt nxt = 0;
    for (int m = 0; m < minimum; ++m) {
        BigInt idx = 0;
        for(BigInt c = C-1; c >= 0; --c) {
            idx += (power(K,c) * nxt);
            nxt++;
            if (nxt == K) {
                nxt -= 1;
            }
        }
        ans ~= [idx];
    }

    foreach (BigInt a; ans) {
        write(" ", a+1);
    }
    writeln("");
}


void main() {
	int n = readln.chomp.to!int;
	for (int i = 1; i <= n; i++) {
        write("Case #", i, ":");
        solve(i);
    }
}
