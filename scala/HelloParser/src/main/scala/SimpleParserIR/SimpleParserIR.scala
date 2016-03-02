package SimpleParserIR

import SimpleLexer._

class SimpleParserIR(lexer: SimpleLexer) {
  var lookahead = lexer.nextToken
  val ir = new IR

  def expression: IR = {
    number
    nextToken match {
      case Token(lexer.OPERATOR, value) => {operator(value); number}
      case Token(lexer.EOF, value) =>
      case token: Token =>
        throw new Exception("found: " + lookahead + ", but not expected")
    }
    ir
  }

  def operator(value: String) = {nextToken; ir.addOperator(value)}

  def number = {
    matches(lexer.NUMBER)
    ir.addOperand(lookahead.value)
  }

  def matches(tokenType: String) = {
    if (!lookahead.tokenType.equals(tokenType))
      throw new Exception("found: " + lookahead + ", but expected: " + tokenType)
  }

  def nextToken: Token = {(lookahead = lexer.nextToken); lookahead}
}

