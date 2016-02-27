package SimpleLexer

import scala.util.parsing.input.CharSequenceReader

case class Token(val tokenType: String, val value: String) {
  override def toString = "[" + tokenType + ": " + value + "]"
}

class SimpleLexer(input: String) {
  val OPERATOR = "OPERATOR"
  val NUMBER = "NUMBER"
  val EOF = "EOF"
  var reader = new CharSequenceReader(input)

  def nextToken() : Token = {
    while (!reader.atEnd) {
      reader.first match {
        case c:Char if (c == '+' || c == '-')
          => return new Token(OPERATOR, takeFirst)
        case c:Char if (c >= '0' && c <= '9')
          => return new Token(NUMBER, takeFirst)
        case c:Char if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
          =>  dump
        case unknown =>
          throw new Exception("Unknown Token(" + unknown + ")")
      }
    }
    new Token(EOF, "")
  }

  def takeFirst() = {
    val first = reader.first
    reader = reader.drop(1)
    first.toString
  }

  def dump() : Unit = reader.first match {
    case c:Char if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
      => takeFirst; dump
    case _ => 
  }
}
