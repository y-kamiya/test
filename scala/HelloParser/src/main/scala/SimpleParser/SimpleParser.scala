package SimpleParser

import SimpleLexer._

class SimpleParser(lexer: SimpleLexer) {
  var lookahead = lexer.nextToken

  def expression = {
    number
    nextToken match {
      case Token(lexer.OPERATOR, value) => {operator; number}
      case Token(lexer.EOF, value) =>
      case token: Token =>
        throw new Exception("found: " + lookahead + ", but not expected")
    }
  }

  def operator = nextToken

  def number = matches(lexer.NUMBER)

  def matches(tokenType: String) = {
    if (!lookahead.tokenType.equals(tokenType))
      throw new Exception("found: " + lookahead + ", but expected: " + tokenType)
  }

  def nextToken: Token = {(lookahead = lexer.nextToken); lookahead}
}
