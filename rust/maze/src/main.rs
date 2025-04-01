use std::collections::HashMap;
use std::fmt;

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
struct Field {
    field: HashMap<Pos, Node>,
    start: Pos,
    goal: Pos,
    width: usize,
    height: usize,
}

impl Field {
    fn new(data: &[&str]) -> Field {
        let mut map = HashMap::new();
        let mut start: Option<Pos> = None;
        let mut goal: Option<Pos> = None;

        for (y, row) in data.iter().enumerate() {
            for (x, c) in row.chars().enumerate() {
                let node_type = match c {
                    'S' => NodeType::Start,
                    'G' => NodeType::Goal,
                    '.' => NodeType::Road,
                    _ => NodeType::Wall,
                };
                let pos = Pos::new(x, y);
                if node_type == NodeType::Start {
                    start = Some(pos);
                }
                if node_type == NodeType::Goal {
                    goal = Some(pos);
                }
                map.insert(pos, Node { node_type: node_type, pos: pos });
            }
        }
        assert!(start.is_some(), "S not found");
        assert!(goal.is_some(), "G not found");

        let h = data.len();
        assert!(h > 1, "data must have at least 2 rows");
        let w = data[0].len();
        assert!(w > 1, "data must have at least 2 cols");

        Self {
            field: map,
            start: start.unwrap(),
            goal: goal.unwrap(),
            width: w,
            height: h,
        }
    }
}

impl fmt::Display for Field {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        for y in 0..self.height {
            for x in 0..self.width {
                let pos = Pos::new(x, y);
                let node = self.field.get(&pos).unwrap();
                let c = match node.node_type {
                    NodeType::Start => 'S',
                    NodeType::Goal => 'G',
                    NodeType::Wall => '#',
                    NodeType::Road => '.',
                };
                write!(f, "{}", c)?;
            }
            write!(f, "\n")?;
        }
        Ok(())
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
    println!("{}", field);

}
