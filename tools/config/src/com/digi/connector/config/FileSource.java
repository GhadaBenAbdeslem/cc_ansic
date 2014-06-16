package com.digi.connector.config;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.digi.connector.config.ConfigGenerator.FileType;

public class FileSource extends FileGenerator {

    private static FileType fileType = FileType.SOURCE;
    private static String SOURCE_NAME = "rci_config";
    
    private static BufferedWriter headerWriter = null;
    private String headerFile = "";

    
	public FileSource(String directoryPath) throws IOException {
		
		super(directoryPath,SOURCE_NAME+ ".c",fileType);
        /* Need to create a header file + source file
         * fileWriter is source file writer. 
         * So we need to create local header file.
         */
        headerFile = SOURCE_NAME + ".h";
        headerWriter = new BufferedWriter(new FileWriter(filePath + headerFile));
        writeHeaderComment(headerWriter);

	}
	
    public void writeHeaderComment(BufferedWriter bufferWriter) throws IOException {
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        Date date = new Date();

        String note_string = "/*\n * This is an auto-generated file - DO NOT EDIT! \n";
        
        if (bufferWriter == headerWriter) 
            note_string += String.format(" * This is a H file generated by %s tool.\n", TOOL_NAME);
        else 
            note_string += String.format(" * This is a C file generated by %s tool.\n", TOOL_NAME);


        note_string += String.format(" * This file was generated on: %s \n", dateFormat.format(date))
                     + String.format(" * The command line arguments were: %s\n", ConfigGenerator.getArgumentLogString())
                     + String.format(" * The version of %s tool was: %s */\n\n", TOOL_NAME, ConfigGenerator.VERSION);
        
        bufferWriter.write(note_string);
        
    }
    
    public void generateFile(ConfigData configData) throws Exception {
        try {

            /* write include header in the header file */
             String headerDefineName = headerFile.replace('.', '_').toLowerCase();
            headerWriter.write(String.format("#ifndef %s\n#define %s\n\n", headerDefineName, headerDefineName));
            headerWriter.write(String.format("%s \"%s\"\n\n", INCLUDE, HEADER_FILENAME));

            fileWriter.write(String.format("%s \"%s\"\n\n", INCLUDE, headerFile));

        	writeGlobalErrorEnumHeader(configData,headerWriter);  
        	writeGroupTypeAndErrorEnum(configData,headerWriter);

            fileWriter.write(String.format("uint32_t CONST FIRMWARE_TARGET_ZERO_VERSION = 0x%X;\n\n", ConfigGenerator.getFirmware()));

            headerWriter.write(String.format("\n\nextern uint32_t CONST FIRMWARE_TARGET_ZERO_VERSION;\n"));
            headerWriter.write("extern unsigned int connector_global_error_COUNT;\n\n");
            headerWriter.write(String.format("extern char CONST * CONST %ss[];\n",GLOBAL_RCI_ERROR));
            headerWriter.write(String.format("extern connector_remote_group_table_t CONST %s[];\n", CONNECTOR_REMOTE_GROUP_TABLE));

            /* Write Define Errors Macros */
            writeDefineRciErrors(configData);

            writeDefineGroupErrors(configData);

            writeDefineGlobalErrors(configData);

            /* write remote all strings in source file */
            writeRemoteAllStrings(configData);

            /* write connector_rci_errors[] */
            writeGlobalErrorStructures(configData);

            /* write structures in source file */
            writeAllStructures(configData);

            headerWriter.write(String.format("\n#endif\n"));
 

            ConfigGenerator.log(String.format("Files created:\n\t%s%s",  filePath, generatedFile));
        if (generatedFile.length() > 0) ConfigGenerator.log(String.format("\t%s%s", filePath, headerFile));


        } catch (IOException e) {
            throw new IOException(e.getMessage());
        }

        finally {
            fileWriter.close();
            if (headerWriter != null) headerWriter.close();
        }

    }
    
    public static BufferedWriter getHeaderWriter(){
    	return headerWriter;
    }
    
}
