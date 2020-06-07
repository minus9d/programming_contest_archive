class Main{
    static function main(){
        var input = Sys.stdin();
        var N = Std.parseInt(input.readLine());
        var S = input.readLine();

        var vecR = new haxe.ds.Vector(N + 1);
        var vecG = new haxe.ds.Vector(N + 1);
        var vecB = new haxe.ds.Vector(N + 1);
        vecR[0] = vecG[0] = vecB[0] = 0;
        for (i in 0...N) {
            vecR[i + 1] = vecR[i];
            vecG[i + 1] = vecG[i];
            vecB[i + 1] = vecB[i];
            if (S.charAt(i) == "R") vecR[i + 1]++;
            if (S.charAt(i) == "G") vecG[i + 1]++;
            if (S.charAt(i) == "B") vecB[i + 1]++;
        } 

        var ans:haxe.Int64 = 0;
        for (i in 0...N - 2) {
            for (j in i...N - 1) {
                var k = j + (j - i);
                var ch1 = S.charAt(i);
                var ch2 = S.charAt(j);
                if (ch1 == ch2) continue;

                if (ch1 == "R" && ch2 == "G" || ch1 == "G" && ch2 == "R") {
                    ans += vecB[N] - vecB[j + 1];
                    if (k < N && S.charAt(k) == "B") ans -= 1;
                }
                else if (ch1 == "R" && ch2 == "B" || ch1 == "B" && ch2 == "R") {
                    ans += vecG[N] - vecG[j + 1];
                    if (k < N && S.charAt(k) == "G") ans -= 1;
                }
                else {
                    ans += vecR[N] - vecR[j + 1];
                    if (k < N && S.charAt(k) == "R") ans -= 1;
                }
            }
        }
        Sys.println(ans);
    }
}
