package CombinatorParser

object CombinatorParserMain {
  def main(args: Array[String]) : Unit = {
    test("Test1", "1 + 2") 
    test("Test2", "1 - 2") 
    test("Test3", "1 * 2") 
    test("Test4", "12 + 3") 
    test("Test5", "++12 4-") 
  }

  def test(caption: String, data: String) {
    println(caption + data)
    val result = new CombinatorParser().parse(data)
    if (result.successful) println("passed.") else println(result)
  }

}
