use std::collections::HashMap;

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
struct Pos {
    x: usize,
    y: usize,
}

impl Pos {
    fn new(x: usize, y: usize) -> Self {
        Pos { x, y }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum NodeType {
    Start,
    Goal,
    Wall,
    Road,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
struct Node {
    node_type: NodeType,
    pos: Pos,
}


#[derive(Debug)]
struct Field(HashMap<Pos, Node>);

impl Field {
    fn new(data: &[&str]) -> Field {
        let mut map = HashMap::new();
        for (y, row) in data.iter().enumerate() {
            for (x, c) in row.chars().enumerate() {
                let node_type = match c {
                    'S' => NodeType::Start,
                    'G' => NodeType::Goal,
                    '#' => NodeType::Wall,
                    '.' => NodeType::Road,
                    _ => continue, //assert!(false, "invalid character of {}", c),
                };
                let pos = Pos::new(x, y);
                map.insert(pos, Node { node_type: node_type, pos: pos });
            }
        }
        Self(map)
    }
}



fn main() {
    let field_sample = [
        "#######",
        "#S....#",
        "##.#.##",
        "####.##",
        "#G....#",
        "#######",
    ];
    let field = Field::new(&field_sample);
    println!("{:?}", field);
}
