object HelloParsing {
    def main(args: Array[String]) {
        val phrase = "Hello Scala World a b c"
        val words = phrase.split(' ')
        words.foreach {println _}
    }
}
