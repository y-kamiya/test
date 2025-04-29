use priority_queue::PriorityQueue;
use std::cmp::Reverse;
use std::collections::{HashMap, HashSet};
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
    Mark,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
struct Node {
    node_type: NodeType,
    pos: Pos,
}

#[derive(Clone, Debug)]
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
                    '#' => NodeType::Wall,
                    _ => NodeType::Road,
                };
                let pos = Pos::new(x, y);
                if node_type == NodeType::Start {
                    start = Some(pos);
                }
                if node_type == NodeType::Goal {
                    goal = Some(pos);
                }
                map.insert(
                    pos,
                    Node {
                        node_type: node_type,
                        pos: pos,
                    },
                );
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

    fn to_goal(&self, from: Pos) -> usize {
        let d = from.x.abs_diff(self.goal.x) + from.y.abs_diff(self.goal.y);
        d as usize
    }

    fn next_pos(&self, pos: Pos) -> Vec<Pos> {
        let mut next = Vec::new();
        for (dx, dy) in [(0, 1), (1, 0), (0, -1), (-1, 0)] {
            let x = pos.x as i32 + dx;
            let y = pos.y as i32 + dy;
            if x < 0 || self.width as i32 <= x || y < 0 || self.height as i32 <= y {
                continue;
            }
            let pos = Pos::new(x as usize, y as usize);
            let node = self.field.get(&pos).unwrap();
            if node.node_type == NodeType::Wall {
                continue;
            }
            next.push(pos);
        }
        next
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
                    NodeType::Mark => 'x',
                };
                write!(f, "{}", c)?;
            }
            write!(f, "\n")?;
        }
        Ok(())
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
struct NodeState {
    parent_pos: Option<Pos>,
    real_cost: usize,
    estimated_cost: usize,
    cost: usize,
}

impl NodeState {
    fn new(parent_pos: Option<Pos>, real_cost: usize, estimated_cost: usize) -> Self {
        Self {
            parent_pos,
            real_cost,
            estimated_cost,
            cost: real_cost + estimated_cost,
        }
    }
}

impl PartialOrd for NodeState {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.cost.partial_cmp(&other.cost)
    }
}

impl Ord for NodeState {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.cost.cmp(&other.cost)
    }
}

type FieldState = HashMap<Pos, NodeState>;

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

    let mut field_state = FieldState::new();
    field_state.insert(
        field.start,
        NodeState::new(None, 0, field.to_goal(field.start)),
    );

    let mut pq = PriorityQueue::new();
    pq.push(field.start, Reverse(field_state[&field.start]));

    let mut closed_set = HashSet::new();

    while let Some((pos, Reverse(state))) = pq.pop() {
        let node = field.field.get(&pos);
        if node.is_none() {
            assert!(false, "node not found on {:?}", pos);
        }

        if node.unwrap().node_type == NodeType::Goal {
            println!("goal found");
            break;
        }

        if closed_set.contains(&pos) {
            continue;
        }
        closed_set.insert(pos);
        println!("current pos: {:?}", pos);

        for next_pos in field.next_pos(pos) {
            if Some(next_pos) == state.parent_pos {
                continue;
            }
            if closed_set.contains(&next_pos) {
                continue;
            }

            let node_state =
                NodeState::new(Some(pos), state.real_cost + 1, field.to_goal(next_pos));
            if let Some(s) = field_state.get(&next_pos) {
                if *s <= node_state {
                    continue;
                }
            }
            let st = field_state.entry(next_pos).or_insert(node_state);
            st.parent_pos = Some(pos);
            st.real_cost = state.real_cost + 1;
            pq.push(next_pos, Reverse(field_state[&next_pos]));
        }
    }

    let mut field_output = field.clone();
    let mut p = field.goal;
    while let Some(s) = field_state.get(&p) {
        println!("{:?}", p);
        let parent_pos = s.parent_pos;
        if parent_pos.is_none() || parent_pos == Some(field.start) {
            break;
        }
        p = s.parent_pos.unwrap();
        field_output.field.get_mut(&p).unwrap().node_type = NodeType::Mark;
    }

    println!("{:}", field_output);
}
