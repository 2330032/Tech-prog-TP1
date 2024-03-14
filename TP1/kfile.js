const fs = require('kmake/fsextra');
// const path = require('path');



let project = new Project('TP1');

project.kore = false;
project.cmd = true;

project.addFile('Sources/**');
project.setDebugDir('Deployment');



resolve(project);
