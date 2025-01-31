const fs = require('kmake/fsextra');



let project = new Project('LabS1J2');

project.kore = false;
project.cmd = true;

project.addFile('Sources/**');
project.setDebugDir('../Deployment');

fs.copyFileSync(process.cwd()+'/labS1J2/test_input.txt','./Deployment/test_input.txt');

resolve(project);
