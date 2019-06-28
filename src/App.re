type todo = {
  id: int,
  text: string,
  completed: bool,
};

let idRef = ref(0);

[@react.component]
let make = () => {
  let (todos, setTodos) = React.useState(() => []);
  let (newTodo, setNewTodo) = React.useState(() => "");
  let addTodo = _ =>
    if (String.trim(newTodo) != "") {
      idRef := idRef^ + 1;
      setTodos(todos =>
        [{id: idRef^, text: newTodo, completed: false}, ...todos]
      );
      setNewTodo(_ => "");
    };
  let toggle = (id: int) => {
    let todos =
      List.map(
        item => item.id === id ? {...item, completed: !item.completed} : item,
        todos,
      );
    setTodos(_ => todos);
  };
  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~flex="1",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexDirection="column",
      (),
    )}>
    <div>
      <input
        value=newTodo
        onChange={event => setNewTodo(event->ReactEvent.Form.target##value)}
        onKeyDown={evt =>
          if (ReactEvent.Keyboard.key(evt) == "Enter") {
            addTodo();
          }
        }
      />
      <button onClick=addTodo> {React.string("Submit")} </button>
    </div>
    <div>
      {List.map(
         todo =>
           <div
             style={ReactDOMRe.Style.make(
               ~display="grid",
               ~gridTemplateColumns="auto 1fr",
               ~maxWidth="300px",
               ~cursor="pointer",
               (),
             )}
             onClick={_ => toggle(todo.id)}
             key={string_of_int(todo.id)}>
             <input type_="checkbox" checked={todo.completed} readOnly=true />
             {React.string(todo.text)}
           </div>,
         todos,
       )
       |> Array.of_list
       |> React.array}
    </div>
  </div>;
};