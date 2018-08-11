declare var require: (x: string) => any;
 
function Main(input: string[]) {
  const N = parseInt(input[0]);
  let flag: boolean = false;
  for (var a = 0; a <= N / 4; a++) {
    if ((N - a * 4) % 7 == 0) {
      flag = true;
    }
  }
  if(flag) {
    console.log('Yes') 
  } else {
    console.log('No')
  }
}

Main(require('fs').readFileSync('/dev/stdin', 'utf8').split('\n'));
