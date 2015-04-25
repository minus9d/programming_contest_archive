import std.stdio; // readln
import std.string; // chomp
import std.array; // split
import std.conv; // to

void main()
{
    string[] input = split(readln());
    int N = to!int(input[0]);
    int S = to!int(input[1]);
    int T = to!int(input[2]);

    int W = to!int(chomp(readln()));
    int ans = 0;

    if (S <= W && W <= T) {
        ++ans;
    }

    for (int i = 0; i < N-1; ++i) {
        int A = to!int(chomp(readln()));
        W += A;
        if (S <= W && W <= T) {
            ++ans;
        }       
    }

    writeln(ans);
}
