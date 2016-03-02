package SimpleParserIR

import scala.collection.mutable.ListBuffer

case class Operator(value: String)

class IR {
  var operator:Operator = null
  val values = ListBuffer[Int]()

  def addOperator(value: String) = {operator = Operator(value)}
  def addOperand(value: String) = {values += value.toInt}
  def operand1 = values(0)
  def operand2 = values(1)
}

