fun main(args: Array<String>) {
    val arr = readLine()!!.split(' ').map{it.toInt()}
    if (arr[0] == arr[1]) {
        println(arr[2])
    }
    else if (arr[0] == arr[2]) {
        println(arr[1])
    }
    else {
        println(arr[0])
    }
}
