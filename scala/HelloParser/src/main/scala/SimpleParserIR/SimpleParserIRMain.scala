package SimpleParserIR

import SimpleLexer._

object SimpleParserIRMain {
  def main(args: Array[String]) : Unit = {
    test("Test1: ", "1 + 2")
    test("Test2: ", "1 - 2")
    test("Test3: ", "1")
    test("Test3: ", "1 * 2")
    test("Test4: ", "12 + 3")
    test("Test5: ", "++12 4-")
  }

  def test(caption: String, data: String) {
    print(caption + data)
    try {
      val ir = new SimpleParserIR(new SimpleLexer(data)).expression
      println(" ==> " + calc(ir))
    } catch {
      case e:Exception => println("failed: " + e)
    }
  }

  def calc(ir:IR) = ir.operator match {
    case Operator("+") => ir.operand1 + ir.operand2
    case Operator("-") => ir.operand1 - ir.operand2
    case _ => ir.operand1
  }
}


