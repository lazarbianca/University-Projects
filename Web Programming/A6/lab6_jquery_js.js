var emptyCell = "16";

function loadPuzzle() {
  console.log("Loading puzzle...");
  pics = new Array(17);
  $.each(pics, function (index) {
    found = true;
    while (found == true) {
      x = 1 + (Math.floor(Math.random() * 1000) % 16);
      found = false;
      for (j = 1; j < index; j++) if (pics[j] == x) found = true;
    }
    pics[index] = x;
    if (x == 16) emptyCell = index;
    console.log("Empty cell: ", emptyCell);
  });
  //	alert(pics+" ");
  //	pics[0] = "0";
  //	pics.sort();
  //	s = "";
  //	for(i=1; i<26; i++) s = s + "\npics[" + i + "]=" + pics[i];
  //	alert("Final:\n"+s);

  var cell;
  $.each(pics, function (index) {
    // cell = $(index)[0];
    cell = document.getElementById(index);
    if (cell) {
      // img = document.createElement("img");
      // if (index != emptyCell)
      //   img.setAttribute("src", "cat" + pics[index] + ".jpg");
      // else img.setAttribute("src", "empty.jpg");
      // cell.appendChild(img);
      var img = $("<img>");

      if (index !== emptyCell) {
        img.attr("src", "cat" + pics[index] + ".jpg");
      } else {
        img.attr("src", "empty.jpg");
      }

      $(cell).append(img);
    }
  });
}

function move(cellID, cell) {
  //	alert(cellID);
  console.log("this=", this, " cell=", cell);
  if (cellID == emptyCell) return;
  const rest = cellID % 4;
  const topPos = cellID > 4 ? cellID - 4 : -1;
  const bottomPos = cellID < 13 ? cellID + 4 : -1;
  const leftPos = rest != 1 ? cellID - 1 : -1;
  const rightPos = rest > 0 ? cellID + 1 : -1;
  // console.log(
  //   "top:",
  //   topPos,
  //   " bottom:",
  //   bottomPos,
  //   " left:",
  //   leftPos,
  //   " right:",
  //   rightPos
  // );
  //	alert(topPos+ " " +bottomPos+" "+leftPos+" "+rightPos);
  if (
    emptyCell != topPos &&
    emptyCell != bottomPos &&
    emptyCell != leftPos &&
    emptyCell != rightPos
  ) {
    // console.log("entered IF");
    return;
  }

  cell1 = document.getElementById(emptyCell);
  console.log("we are moving: ", emptyCell);
  img1 = cell1.children[0];
  // img1 = cell1.firstChild;
  img = cell.children[0];
  // img = cell.firstChild;
  cell.removeChild(cell.children[0]);
  cell1.removeChild(cell1.children[0]);

  cell.appendChild(img1);
  cell1.appendChild(img);
  emptyCell = cellID;

  // var cell1 = $("#" + emptyCell);
  // console.log("we are moving: ", emptyCell);
  // var img1 = cell1.children[0];
  // var img = cell.children[0];

  // cell.empty;
  // cell1.empty;

  // cell.append(img1);
  // cell1.append(img);
  // emptyCell = cellID;
}
