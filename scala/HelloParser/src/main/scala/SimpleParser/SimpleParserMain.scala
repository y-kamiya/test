package SimpleParser

import SimpleLexer._

object SimpleParserMain {
  def main(args: Array[String]) : Unit = {
    test("Test1: ", "1 + 2")
    test("Test2: ", "1 - 2")
    test("Test3: ", "1 * 2")
    test("Test4: ", "12 + 3")
    test("Test5: ", "++12 4-")
  }

  def test(caption: String, data: String) {
    println(caption + data)
    try {
      new SimpleParser(new SimpleLexer(data)).expression
      println("passed.")
    } catch {
      case e:Exception => println("failed: " + e)
    }
  }
}

