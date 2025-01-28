const fs = require('kmake/fsextra');
// const path = require('path');



let project = new Project('LabS1J1');

project.kore = false;
project.cmd = true;

project.addFile('Sources/**');
project.setDebugDir('../Deployment');

fs.copyFileSync(process.cwd()+'/labS1J1/test_input.txt',process.cwd()+'/Deployment/test_input.txt');

resolve(project);
