package SimpleLexer

object SimpleLexerMain {
  def main(args: Array[String]) : Unit = {
    test("Test1: ", "1 + 2")
    test("Test2: ", "1 - 2")
    test("Test3: ", "++12 4-")
  }

  def test(caption: String, data: String) {
    println(caption + data)
    read(new SimpleLexer(data))
  }

  def read(lexer: SimpleLexer) : Unit = lexer.nextToken match {
    case Token(lexer.EOF, value) => println()
    case token:Token => print(token); read(lexer)
  }

}

