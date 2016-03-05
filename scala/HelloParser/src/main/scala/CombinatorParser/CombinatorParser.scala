package CombinatorParser

import scala.util.parsing.combinator._

class CombinatorParser extends JavaTokenParsers {
  def parse(data: String) = parseAll(expression, data)

  def expression: Parser[Any] =
    (number~"+"~number) | (number~"-"~number) | number

  def number: Parser[String] = """[0-9]""".r
}
